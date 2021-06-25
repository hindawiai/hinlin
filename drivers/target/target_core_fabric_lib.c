<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * Filename:  target_core_fabric_lib.c
 *
 * This file contains generic high level protocol identअगरier and PR
 * handlers क्रम TCM fabric modules
 *
 * (c) Copyright 2010-2013 Datera, Inc.
 *
 * Nicholas A. Bellinger <nab@linux-iscsi.org>
 *
 ******************************************************************************/

/*
 * See SPC4, section 7.5 "Protocol specific parameters" क्रम details
 * on the क्रमmats implemented in this file.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <scsi/scsi_proto.h>

#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>

#समावेश "target_core_internal.h"
#समावेश "target_core_pr.h"


अटल पूर्णांक sas_get_pr_transport_id(
	काष्ठा se_node_acl *nacl,
	पूर्णांक *क्रमmat_code,
	अचिन्हित अक्षर *buf)
अणु
	पूर्णांक ret;

	/* Skip over 'naa. prefix */
	ret = hex2bin(&buf[4], &nacl->initiatorname[4], 8);
	अगर (ret) अणु
		pr_debug("%s: invalid hex string\n", __func__);
		वापस ret;
	पूर्ण

	वापस 24;
पूर्ण

अटल पूर्णांक fc_get_pr_transport_id(
	काष्ठा se_node_acl *se_nacl,
	पूर्णांक *क्रमmat_code,
	अचिन्हित अक्षर *buf)
अणु
	अचिन्हित अक्षर *ptr;
	पूर्णांक i, ret;
	u32 off = 8;

	/*
	 * We convert the ASCII क्रमmatted N Port name पूर्णांकo a binary
	 * encoded TransportID.
	 */
	ptr = &se_nacl->initiatorname[0];
	क्रम (i = 0; i < 23; ) अणु
		अगर (!म_भेदन(&ptr[i], ":", 1)) अणु
			i++;
			जारी;
		पूर्ण
		ret = hex2bin(&buf[off++], &ptr[i], 1);
		अगर (ret < 0) अणु
			pr_debug("%s: invalid hex string\n", __func__);
			वापस ret;
		पूर्ण
		i += 2;
	पूर्ण
	/*
	 * The FC Transport ID is a hardcoded 24-byte length
	 */
	वापस 24;
पूर्ण

अटल पूर्णांक sbp_get_pr_transport_id(
	काष्ठा se_node_acl *nacl,
	पूर्णांक *क्रमmat_code,
	अचिन्हित अक्षर *buf)
अणु
	पूर्णांक ret;

	ret = hex2bin(&buf[8], nacl->initiatorname, 8);
	अगर (ret) अणु
		pr_debug("%s: invalid hex string\n", __func__);
		वापस ret;
	पूर्ण

	वापस 24;
पूर्ण

अटल पूर्णांक srp_get_pr_transport_id(
	काष्ठा se_node_acl *nacl,
	पूर्णांक *क्रमmat_code,
	अचिन्हित अक्षर *buf)
अणु
	स्थिर अक्षर *p;
	अचिन्हित len, count, leading_zero_bytes;
	पूर्णांक rc;

	p = nacl->initiatorname;
	अगर (strnहालcmp(p, "0x", 2) == 0)
		p += 2;
	len = म_माप(p);
	अगर (len % 2)
		वापस -EINVAL;

	count = min(len / 2, 16U);
	leading_zero_bytes = 16 - count;
	स_रखो(buf + 8, 0, leading_zero_bytes);
	rc = hex2bin(buf + 8 + leading_zero_bytes, p, count);
	अगर (rc < 0) अणु
		pr_debug("hex2bin failed for %s: %d\n", p, rc);
		वापस rc;
	पूर्ण

	वापस 24;
पूर्ण

अटल पूर्णांक iscsi_get_pr_transport_id(
	काष्ठा se_node_acl *se_nacl,
	काष्ठा t10_pr_registration *pr_reg,
	पूर्णांक *क्रमmat_code,
	अचिन्हित अक्षर *buf)
अणु
	u32 off = 4, padding = 0;
	पूर्णांक isid_len;
	u16 len = 0;

	spin_lock_irq(&se_nacl->nacl_sess_lock);
	/*
	 * Only null terminate the last field.
	 *
	 * From spc4r37 section 7.6.4.6: TransportID क्रम initiator ports using
	 * SCSI over iSCSI.
	 *
	 * Table 507 TPID=0 Initiator device TransportID
	 *
	 * The null-terminated, null-padded (see 4.3.2) ISCSI NAME field shall
	 * contain the iSCSI name of an iSCSI initiator node (see RFC 7143).
	 * The first ISCSI NAME field byte containing an ASCII null अक्षरacter
	 * terminates the ISCSI NAME field without regard क्रम the specअगरied
	 * length of the iSCSI TransportID or the contents of the ADDITIONAL
	 * LENGTH field.
	 */
	len = प्र_लिखो(&buf[off], "%s", se_nacl->initiatorname);
	off += len;
	अगर ((*क्रमmat_code == 1) && (pr_reg->isid_present_at_reg)) अणु
		/*
		 * Set FORMAT CODE 01b क्रम iSCSI Initiator port TransportID
		 * क्रमmat.
		 */
		buf[0] |= 0x40;
		/*
		 * From spc4r37 Section 7.6.4.6
		 *
		 * Table 508 TPID=1 Initiator port TransportID.
		 *
		 * The ISCSI NAME field shall not be null-terminated
		 * (see 4.3.2) and shall not be padded.
		 *
		 * The SEPARATOR field shall contain the five ASCII
		 * अक्षरacters ",i,0x".
		 *
		 * The null-terminated, null-padded ISCSI INITIATOR SESSION ID
		 * field shall contain the iSCSI initiator session identअगरier
		 * (see RFC 3720) in the क्रमm of ASCII अक्षरacters that are the
		 * hexadecimal digits converted from the binary iSCSI initiator
		 * session identअगरier value. The first ISCSI INITIATOR SESSION
		 * ID field byte containing an ASCII null अक्षरacter terminates
		 * the ISCSI INITIATOR SESSION ID field without regard क्रम the
		 * specअगरied length of the iSCSI TransportID or the contents
		 * of the ADDITIONAL LENGTH field.
		 */
		buf[off++] = 0x2c; /* ASCII Character: "," */
		buf[off++] = 0x69; /* ASCII Character: "i" */
		buf[off++] = 0x2c; /* ASCII Character: "," */
		buf[off++] = 0x30; /* ASCII Character: "0" */
		buf[off++] = 0x78; /* ASCII Character: "x" */
		len += 5;

		isid_len = प्र_लिखो(buf + off, "%s", pr_reg->pr_reg_isid);
		off += isid_len;
		len += isid_len;
	पूर्ण
	buf[off] = '\0';
	len += 1;
	spin_unlock_irq(&se_nacl->nacl_sess_lock);
	/*
	 * The ADDITIONAL LENGTH field specअगरies the number of bytes that follow
	 * in the TransportID. The additional length shall be at least 20 and
	 * shall be a multiple of four.
	*/
	padding = ((-len) & 3);
	अगर (padding != 0)
		len += padding;

	put_unaligned_be16(len, &buf[2]);
	/*
	 * Increment value क्रम total payload + header length क्रम
	 * full status descriptor
	 */
	len += 4;

	वापस len;
पूर्ण

अटल पूर्णांक iscsi_get_pr_transport_id_len(
	काष्ठा se_node_acl *se_nacl,
	काष्ठा t10_pr_registration *pr_reg,
	पूर्णांक *क्रमmat_code)
अणु
	u32 len = 0, padding = 0;

	spin_lock_irq(&se_nacl->nacl_sess_lock);
	len = म_माप(se_nacl->initiatorname);
	/*
	 * Add extra byte क्रम शून्य terminator
	 */
	len++;
	/*
	 * If there is ISID present with the registration, use क्रमmat code:
	 * 01b: iSCSI Initiator port TransportID क्रमmat
	 *
	 * If there is not an active iSCSI session, use क्रमmat code:
	 * 00b: iSCSI Initiator device TransportID क्रमmat
	 */
	अगर (pr_reg->isid_present_at_reg) अणु
		len += 5; /* For ",i,0x" ASCII separator */
		len += म_माप(pr_reg->pr_reg_isid);
		*क्रमmat_code = 1;
	पूर्ण अन्यथा
		*क्रमmat_code = 0;
	spin_unlock_irq(&se_nacl->nacl_sess_lock);
	/*
	 * The ADDITIONAL LENGTH field specअगरies the number of bytes that follow
	 * in the TransportID. The additional length shall be at least 20 and
	 * shall be a multiple of four.
	 */
	padding = ((-len) & 3);
	अगर (padding != 0)
		len += padding;
	/*
	 * Increment value क्रम total payload + header length क्रम
	 * full status descriptor
	 */
	len += 4;

	वापस len;
पूर्ण

अटल अक्षर *iscsi_parse_pr_out_transport_id(
	काष्ठा se_portal_group *se_tpg,
	अक्षर *buf,
	u32 *out_tid_len,
	अक्षर **port_nexus_ptr)
अणु
	अक्षर *p;
	पूर्णांक i;
	u8 क्रमmat_code = (buf[0] & 0xc0);
	/*
	 * Check क्रम FORMAT CODE 00b or 01b from spc4r17, section 7.5.4.6:
	 *
	 *       TransportID क्रम initiator ports using SCSI over iSCSI,
	 *       from Table 388 -- iSCSI TransportID क्रमmats.
	 *
	 *    00b     Initiator port is identअगरied using the world wide unique
	 *            SCSI device name of the iSCSI initiator
	 *            device containing the initiator port (see table 389).
	 *    01b     Initiator port is identअगरied using the world wide unique
	 *            initiator port identअगरier (see table 390).10b to 11b
	 *            Reserved
	 */
	अगर ((क्रमmat_code != 0x00) && (क्रमmat_code != 0x40)) अणु
		pr_err("Illegal format code: 0x%02x for iSCSI"
			" Initiator Transport ID\n", क्रमmat_code);
		वापस शून्य;
	पूर्ण
	/*
	 * If the caller wants the TransportID Length, we set that value क्रम the
	 * entire iSCSI Tarnsport ID now.
	 */
	अगर (out_tid_len) अणु
		/* The shअगरt works thanks to पूर्णांकeger promotion rules */
		*out_tid_len = get_unaligned_be16(&buf[2]);
		/* Add four bytes क्रम iSCSI Transport ID header */
		*out_tid_len += 4;
	पूर्ण

	/*
	 * Check क्रम ',i,0x' separator between iSCSI Name and iSCSI Initiator
	 * Session ID as defined in Table 390 - iSCSI initiator port TransportID
	 * क्रमmat.
	 */
	अगर (क्रमmat_code == 0x40) अणु
		p = म_माला(&buf[4], ",i,0x");
		अगर (!p) अणु
			pr_err("Unable to locate \",i,0x\" separator"
				" for Initiator port identifier: %s\n",
				&buf[4]);
			वापस शून्य;
		पूर्ण
		*p = '\0'; /* Terminate iSCSI Name */
		p += 5; /* Skip over ",i,0x" separator */

		*port_nexus_ptr = p;
		/*
		 * Go ahead and करो the lower हाल conversion of the received
		 * 12 ASCII अक्षरacters representing the ISID in the TransportID
		 * क्रम comparison against the running iSCSI session's ISID from
		 * iscsi_target.c:lio_sess_get_initiator_sid()
		 */
		क्रम (i = 0; i < 12; i++) अणु
			/*
			 * The first ISCSI INITIATOR SESSION ID field byte
			 * containing an ASCII null अक्षरacter terminates the
			 * ISCSI INITIATOR SESSION ID field without regard क्रम
			 * the specअगरied length of the iSCSI TransportID or the
			 * contents of the ADDITIONAL LENGTH field.
			 */
			अगर (*p == '\0')
				अवरोध;

			अगर (है_अंक(*p)) अणु
				p++;
				जारी;
			पूर्ण
			*p = छोटे(*p);
			p++;
		पूर्ण
	पूर्ण अन्यथा
		*port_nexus_ptr = शून्य;

	वापस &buf[4];
पूर्ण

पूर्णांक target_get_pr_transport_id_len(काष्ठा se_node_acl *nacl,
		काष्ठा t10_pr_registration *pr_reg, पूर्णांक *क्रमmat_code)
अणु
	चयन (nacl->se_tpg->proto_id) अणु
	हाल SCSI_PROTOCOL_FCP:
	हाल SCSI_PROTOCOL_SBP:
	हाल SCSI_PROTOCOL_SRP:
	हाल SCSI_PROTOCOL_SAS:
		अवरोध;
	हाल SCSI_PROTOCOL_ISCSI:
		वापस iscsi_get_pr_transport_id_len(nacl, pr_reg, क्रमmat_code);
	शेष:
		pr_err("Unknown proto_id: 0x%02x\n", nacl->se_tpg->proto_id);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Most transports use a fixed length 24 byte identअगरier.
	 */
	*क्रमmat_code = 0;
	वापस 24;
पूर्ण

पूर्णांक target_get_pr_transport_id(काष्ठा se_node_acl *nacl,
		काष्ठा t10_pr_registration *pr_reg, पूर्णांक *क्रमmat_code,
		अचिन्हित अक्षर *buf)
अणु
	चयन (nacl->se_tpg->proto_id) अणु
	हाल SCSI_PROTOCOL_SAS:
		वापस sas_get_pr_transport_id(nacl, क्रमmat_code, buf);
	हाल SCSI_PROTOCOL_SBP:
		वापस sbp_get_pr_transport_id(nacl, क्रमmat_code, buf);
	हाल SCSI_PROTOCOL_SRP:
		वापस srp_get_pr_transport_id(nacl, क्रमmat_code, buf);
	हाल SCSI_PROTOCOL_FCP:
		वापस fc_get_pr_transport_id(nacl, क्रमmat_code, buf);
	हाल SCSI_PROTOCOL_ISCSI:
		वापस iscsi_get_pr_transport_id(nacl, pr_reg, क्रमmat_code,
				buf);
	शेष:
		pr_err("Unknown proto_id: 0x%02x\n", nacl->se_tpg->proto_id);
		वापस -EINVAL;
	पूर्ण
पूर्ण

स्थिर अक्षर *target_parse_pr_out_transport_id(काष्ठा se_portal_group *tpg,
		अक्षर *buf, u32 *out_tid_len, अक्षर **port_nexus_ptr)
अणु
	u32 offset;

	चयन (tpg->proto_id) अणु
	हाल SCSI_PROTOCOL_SAS:
		/*
		 * Assume the FORMAT CODE 00b from spc4r17, 7.5.4.7 TransportID
		 * क्रम initiator ports using SCSI over SAS Serial SCSI Protocol.
		 */
		offset = 4;
		अवरोध;
	हाल SCSI_PROTOCOL_SBP:
	हाल SCSI_PROTOCOL_SRP:
	हाल SCSI_PROTOCOL_FCP:
		offset = 8;
		अवरोध;
	हाल SCSI_PROTOCOL_ISCSI:
		वापस iscsi_parse_pr_out_transport_id(tpg, buf, out_tid_len,
					port_nexus_ptr);
	शेष:
		pr_err("Unknown proto_id: 0x%02x\n", tpg->proto_id);
		वापस शून्य;
	पूर्ण

	*port_nexus_ptr = शून्य;
	*out_tid_len = 24;
	वापस buf + offset;
पूर्ण
