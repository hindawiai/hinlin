<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _N2_CORE_H
#घोषणा _N2_CORE_H

#अगर_अघोषित __ASSEMBLY__

काष्ठा ino_blob अणु
	u64			पूर्णांकr;
	u64			ino;
पूर्ण;

काष्ठा spu_mdesc_info अणु
	u64			cfg_handle;
	काष्ठा ino_blob		*ino_table;
	पूर्णांक			num_पूर्णांकrs;
पूर्ण;

काष्ठा n2_crypto अणु
	काष्ठा spu_mdesc_info	cwq_info;
	काष्ठा list_head	cwq_list;
पूर्ण;

काष्ठा n2_mau अणु
	काष्ठा spu_mdesc_info	mau_info;
	काष्ठा list_head	mau_list;
पूर्ण;

#घोषणा CWQ_ENTRY_SIZE		64
#घोषणा CWQ_NUM_ENTRIES		64

#घोषणा MAU_ENTRY_SIZE		64
#घोषणा MAU_NUM_ENTRIES		64

काष्ठा cwq_initial_entry अणु
	u64			control;
	u64			src_addr;
	u64			auth_key_addr;
	u64			auth_iv_addr;
	u64			final_auth_state_addr;
	u64			enc_key_addr;
	u64			enc_iv_addr;
	u64			dest_addr;
पूर्ण;

काष्ठा cwq_ext_entry अणु
	u64			len;
	u64			src_addr;
	u64			resv1;
	u64			resv2;
	u64			resv3;
	u64			resv4;
	u64			resv5;
	u64			resv6;
पूर्ण;

काष्ठा cwq_final_entry अणु
	u64			control;
	u64			src_addr;
	u64			resv1;
	u64			resv2;
	u64			resv3;
	u64			resv4;
	u64			resv5;
	u64			resv6;
पूर्ण;

#घोषणा CONTROL_LEN			0x000000000000ffffULL
#घोषणा CONTROL_LEN_SHIFT		0
#घोषणा CONTROL_HMAC_KEY_LEN		0x0000000000ff0000ULL
#घोषणा CONTROL_HMAC_KEY_LEN_SHIFT	16
#घोषणा CONTROL_ENC_TYPE		0x00000000ff000000ULL
#घोषणा CONTROL_ENC_TYPE_SHIFT		24
#घोषणा  ENC_TYPE_ALG_RC4_STREAM	0x00ULL
#घोषणा  ENC_TYPE_ALG_RC4_NOSTREAM	0x04ULL
#घोषणा  ENC_TYPE_ALG_DES		0x08ULL
#घोषणा  ENC_TYPE_ALG_3DES		0x0cULL
#घोषणा  ENC_TYPE_ALG_AES128		0x10ULL
#घोषणा  ENC_TYPE_ALG_AES192		0x14ULL
#घोषणा  ENC_TYPE_ALG_AES256		0x18ULL
#घोषणा  ENC_TYPE_ALG_RESERVED		0x1cULL
#घोषणा  ENC_TYPE_ALG_MASK		0x1cULL
#घोषणा  ENC_TYPE_CHAINING_ECB		0x00ULL
#घोषणा  ENC_TYPE_CHAINING_CBC		0x01ULL
#घोषणा  ENC_TYPE_CHAINING_CFB		0x02ULL
#घोषणा  ENC_TYPE_CHAINING_COUNTER	0x03ULL
#घोषणा  ENC_TYPE_CHAINING_MASK		0x03ULL
#घोषणा CONTROL_AUTH_TYPE		0x0000001f00000000ULL
#घोषणा CONTROL_AUTH_TYPE_SHIFT		32
#घोषणा  AUTH_TYPE_RESERVED		0x00ULL
#घोषणा  AUTH_TYPE_MD5			0x01ULL
#घोषणा  AUTH_TYPE_SHA1			0x02ULL
#घोषणा  AUTH_TYPE_SHA256		0x03ULL
#घोषणा  AUTH_TYPE_CRC32		0x04ULL
#घोषणा  AUTH_TYPE_HMAC_MD5		0x05ULL
#घोषणा  AUTH_TYPE_HMAC_SHA1		0x06ULL
#घोषणा  AUTH_TYPE_HMAC_SHA256		0x07ULL
#घोषणा  AUTH_TYPE_TCP_CHECKSUM		0x08ULL
#घोषणा  AUTH_TYPE_SSL_HMAC_MD5		0x09ULL
#घोषणा  AUTH_TYPE_SSL_HMAC_SHA1	0x0aULL
#घोषणा  AUTH_TYPE_SSL_HMAC_SHA256	0x0bULL
#घोषणा CONTROL_STRAND			0x000000e000000000ULL
#घोषणा CONTROL_STRAND_SHIFT		37
#घोषणा CONTROL_HASH_LEN		0x0000ff0000000000ULL
#घोषणा CONTROL_HASH_LEN_SHIFT		40
#घोषणा CONTROL_INTERRUPT		0x0001000000000000ULL
#घोषणा CONTROL_STORE_FINAL_AUTH_STATE	0x0002000000000000ULL
#घोषणा CONTROL_RESERVED		0x001c000000000000ULL
#घोषणा CONTROL_HV_DONE			0x0004000000000000ULL
#घोषणा CONTROL_HV_PROTOCOL_ERROR	0x0008000000000000ULL
#घोषणा CONTROL_HV_HARDWARE_ERROR	0x0010000000000000ULL
#घोषणा CONTROL_END_OF_BLOCK		0x0020000000000000ULL
#घोषणा CONTROL_START_OF_BLOCK		0x0040000000000000ULL
#घोषणा CONTROL_ENCRYPT			0x0080000000000000ULL
#घोषणा CONTROL_OPCODE			0xff00000000000000ULL
#घोषणा CONTROL_OPCODE_SHIFT		56
#घोषणा  OPCODE_INPLACE_BIT		0x80ULL
#घोषणा  OPCODE_SSL_KEYBLOCK		0x10ULL
#घोषणा  OPCODE_COPY			0x20ULL
#घोषणा  OPCODE_ENCRYPT			0x40ULL
#घोषणा  OPCODE_AUTH_MAC		0x41ULL

#पूर्ण_अगर /* !(__ASSEMBLY__) */

/* NCS v2.0 hypervisor पूर्णांकerfaces */
#घोषणा HV_NCS_QTYPE_MAU		0x01
#घोषणा HV_NCS_QTYPE_CWQ		0x02

/* ncs_qconf()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_NCS_QCONF
 * ARG0:	Queue type (HV_NCS_QTYPE_अणुMAU,CWQपूर्ण)
 * ARG1:	Real address of queue, or handle क्रम unconfigure
 * ARG2:	Number of entries in queue, zero क्रम unconfigure
 * RET0:	status
 * RET1:	queue handle
 *
 * Configure a queue in the stream processing unit.
 *
 * The real address given as the base must be 64-byte
 * aligned.
 *
 * The queue size can range from a minimum of 2 to a maximum
 * of 64.  The queue size must be a घातer of two.
 *
 * To unconfigure a queue, specअगरy a length of zero and place
 * the queue handle पूर्णांकo ARG1.
 *
 * On configure success the hypervisor will set the FIRST, HEAD,
 * and TAIL रेजिस्टरs to the address of the first entry in the
 * queue.  The LAST रेजिस्टर will be set to poपूर्णांक to the last
 * entry in the queue.
 */
#घोषणा HV_FAST_NCS_QCONF		0x111

/* ncs_qinfo()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_NCS_QINFO
 * ARG0:	Queue handle
 * RET0:	status
 * RET1:	Queue type (HV_NCS_QTYPE_अणुMAU,CWQपूर्ण)
 * RET2:	Queue base address
 * RET3:	Number of entries
 */
#घोषणा HV_FAST_NCS_QINFO		0x112

/* ncs_gethead()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_NCS_GETHEAD
 * ARG0:	Queue handle
 * RET0:	status
 * RET1:	queue head offset
 */
#घोषणा HV_FAST_NCS_GETHEAD		0x113

/* ncs_gettail()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_NCS_GETTAIL
 * ARG0:	Queue handle
 * RET0:	status
 * RET1:	queue tail offset
 */
#घोषणा HV_FAST_NCS_GETTAIL		0x114

/* ncs_settail()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_NCS_SETTAIL
 * ARG0:	Queue handle
 * ARG1:	New tail offset
 * RET0:	status
 */
#घोषणा HV_FAST_NCS_SETTAIL		0x115

/* ncs_qhandle_to_devino()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_NCS_QHANDLE_TO_DEVINO
 * ARG0:	Queue handle
 * RET0:	status
 * RET1:	devino
 */
#घोषणा HV_FAST_NCS_QHANDLE_TO_DEVINO	0x116

/* ncs_sethead_marker()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_NCS_SETHEAD_MARKER
 * ARG0:	Queue handle
 * ARG1:	New head offset
 * RET0:	status
 */
#घोषणा HV_FAST_NCS_SETHEAD_MARKER	0x117

#अगर_अघोषित __ASSEMBLY__
बाह्य अचिन्हित दीर्घ sun4v_ncs_qconf(अचिन्हित दीर्घ queue_type,
				     अचिन्हित दीर्घ queue_ra,
				     अचिन्हित दीर्घ num_entries,
				     अचिन्हित दीर्घ *qhandle);
बाह्य अचिन्हित दीर्घ sun4v_ncs_qinfo(अचिन्हित दीर्घ qhandle,
				     अचिन्हित दीर्घ *queue_type,
				     अचिन्हित दीर्घ *queue_ra,
				     अचिन्हित दीर्घ *num_entries);
बाह्य अचिन्हित दीर्घ sun4v_ncs_gethead(अचिन्हित दीर्घ qhandle,
				       अचिन्हित दीर्घ *head);
बाह्य अचिन्हित दीर्घ sun4v_ncs_gettail(अचिन्हित दीर्घ qhandle,
				       अचिन्हित दीर्घ *tail);
बाह्य अचिन्हित दीर्घ sun4v_ncs_settail(अचिन्हित दीर्घ qhandle,
				       अचिन्हित दीर्घ tail);
बाह्य अचिन्हित दीर्घ sun4v_ncs_qhandle_to_devino(अचिन्हित दीर्घ qhandle,
						 अचिन्हित दीर्घ *devino);
बाह्य अचिन्हित दीर्घ sun4v_ncs_sethead_marker(अचिन्हित दीर्घ qhandle,
					      अचिन्हित दीर्घ head);
#पूर्ण_अगर /* !(__ASSEMBLY__) */

#पूर्ण_अगर /* _N2_CORE_H */
